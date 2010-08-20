#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "appcore/logging.h"
#include "renderers/opengl.h"
#include "cubeworld.h"
#include "cubedata.h"
#include "camera.h"
#include "gameapp.h"

#include "mathlib.h"

#include <cassert>
#include <iostream>

using namespace Rogue;

const int DEFAULT_POS = 0;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int DEFAULT_FOV = 90;
const int KEY_ESC = 27;

Camera GCamera;

bool checkForErrors();
void initScene();
void resizeScene( int w, int h );

void glutIdleFunc();
void doRenderScene();
void handleMenuItemSelection( int id );
void handleKeyboard( unsigned char key, int x, int y );
void handleSpecialKeys( int key, int x, int y );
void handleMouseWheel( int button, int dir, int x, int y );
void drawCube();
float calcFPS();
void mouseMovement( int x, int y );

void startRenderer( int argc, char* argv[] )
{
    //
    // Create and initialie GLUT
    //
    INFO("gui") << "Creating render window" << ENDLOG;
    glutInit(&argc, argv);

    // Create the main rendering window
    glutInitWindowPosition( DEFAULT_POS, DEFAULT_POS );
    glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

    glutCreateWindow("Scott's Roguelike");

    // Register call backs
    glutDisplayFunc(doRenderScene);
    glutReshapeFunc(resizeScene);
    glutIdleFunc(glutIdleFunc);
    glutKeyboardFunc(handleKeyboard);
    glutSpecialFunc(handleSpecialKeys);
    glutMouseWheelFunc(handleMouseWheel);
    glutPassiveMotionFunc(mouseMovement);

    //
    // Initialize the game loop, and then let OpenGL set up default init
    // settings (TODO change this to renderer, set defaults that can
    // be changed by game loop)
    // TODO change function call to a class that gets created, so we can
    // have multiple scenes
    //
    initScene();

    glutMainLoop();

    // Make sure nothing went wrong
    checkForErrors();
}

float calcFPS()
{
    static int lastTime    = 0;
    static int nextTime    = 0;
    static int   frames    = 0;

    static int bestFrameTime  = -1;
    static int worstFrameTime = 0;

    const  int updateInterval = 2000;

    // init
    int nowTime   = glutGet( GLUT_ELAPSED_TIME );
    int deltaTime = nowTime - lastTime;

    if ( lastTime == 0 )
    {
        lastTime  = nowTime;
        nextTime += nowTime + updateInterval;
        return 0.0f;
    }

    // update stats
    frames++;

    // calculate best frame time, worst frame time
    if ( deltaTime < bestFrameTime || bestFrameTime == -1 )
    {
        bestFrameTime = deltaTime;
    }
    else if ( deltaTime > worstFrameTime )
    {
        worstFrameTime = deltaTime;
    }

    // time to re-calc our averages and spit them out?
    if ( nowTime > nextTime )
    {
        float fps = (float) frames / ((float)updateInterval/1000.0f);
        float avg = ((float)updateInterval/1000.0f) / (float) frames;

        std::cout << "Frames per second : " << fps << std::endl
                  << "Average frame time: " << avg 
                                            << std::endl
                  << "Best frame time:    " << bestFrameTime
                                            << std::endl
                  << "Worst frame time:   " << worstFrameTime
                                            << std::endl;

        // reset
        nextTime += updateInterval;
        bestFrameTime = -1;
        worstFrameTime = 0;
        frames    = 0;
    }


    lastTime = nowTime;
}

void stopRenderer()
{

}

void doRenderScene()
{
    // TODO eliminate the call to gametick, find a way to only render the
    // last submitted frame (decouple frames/ticks)
    doGameTick( 0.0f, 0.0f );
    glutPostRedisplay();
}

void glutIdleFunc()
{
    // Process a tick, and then draw the frame
    doGameTick( 0.0f, 0.0f );
    glutPostRedisplay();
}

// helper function, remove me
void renderScene( const World& world )
{
    renderScene( world, GCamera );
}

struct CubeRenderVisitor : public Rogue::CubeVisitor
{
public:
    CubeRenderVisitor( const Camera& camera )
        : m_camera(camera)
    {
    }

    void process( const WorldCube& cube )
    {
        Point pos = cube.position();

        // determine color
        float color[3] = { 0.0, 0.0, 0.0 };

        if ( cube.hasData() )
        {
            switch ( cube->baseMaterial() )
            {
                case Materials::Grass:
                    color[1] = 1.0;
                    break;

                case Materials::Dirt:
                    color[0] = 0.6;
                    color[1] = 0.3;
                    break;

                case Materials::Water:
                    color[2] = 1.0;
                    break;

                case Materials::Rock:
                    color[0] = 0.2; color[1] = 0.2; color[2] = 0.2;
                    break;

                case Materials::Sand:
                    color[0] = 0.8; color[1] = 0.8; color[2] = 0.3;
                    break;

                case Materials::Wood:
                    color[0] = 0.7;
                    color[1] = 0.5;
                    break;

                case Materials::Liquid:
                    color[1] = 0.45;
                    break;

                default:
                    color[0] = 0.5; color[1] = 0.5; color[2] = 0.5;
                    break;
            }
        }
        else
        {
            color[0] = 1.0; color[1] = 1.0; color[2] = 1.0;
        }
        
        //
        // Colors
        //
        float ambient[3] = { 0.25, 0.25, 0.25 };

        glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE );
        glMaterialfv( GL_FRONT, GL_AMBIENT, (const GLfloat*) &color );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, (const GLfloat*) &color );

        //
        // Draw a cube
        //
        glPushMatrix();
        glTranslatef( pos[0], pos[2], -pos[1] );

//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        drawCube();

        glPopMatrix();
    }

private:
    Camera m_camera;
};

void renderScene( const World& world, const Camera& camera )
{
    // Clear the rendering buffrs
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Reset model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Move the camera back a little bit (so we can see the origin -Z)
    Vec3 lookAt = camera.direction() * camera.viewDistance();
    Vec3 center = camera.center();
    Vec3 up     = camera.up();

    gluLookAt( center[0], center[1], center[2],
               lookAt[0], lookAt[1], lookAt[2],
               up[0],     up[1],     up[2] );

    //
    // Lighting
    //
    GLfloat lightPos[4] = { 0.0, 5.0, 2.0, 1.0 };
    GLfloat lightAmb[4] = { 0.75, 0.75, 0.75, 1.0 };
    GLfloat lightDif[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightSpc[4] = { 1.0, 0.25, 0.25, 1.0 };

    glLightfv( GL_LIGHT0, GL_POSITION, lightPos );
    glLightfv( GL_LIGHT0, GL_AMBIENT,  lightAmb );
    glLightfv( GL_LIGHT0, GL_DIFFUSE,  lightDif );
    glLightfv( GL_LIGHT0, GL_SPECULAR, lightSpc );

    //
    // Yay braindead renderer.
    //
    CubeRenderVisitor visitor(camera);
    world.visitAllCubes( visitor );

    
    checkForErrors();

    calcFPS();

    // Draw it
    glutSwapBuffers();
}

void drawCube()
{
    glBegin(GL_QUADS);
/*        glNormal3f( 0.0f, 1.0f, 0.0f );
        glVertex3f( 1.0f, 1.0f,0.0f);			// Top Right Of The Quad (Top)
        glVertex3f(0.0f, 1.0f,0.0f);			// Top Left Of The Quad (Top)
        glVertex3f(0.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
        glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)

        glNormal3f( 0.0f, -1.0f, 0.0f );
        glVertex3f( 1.0f,0.0f, 1.0f);			// Top Right Of The Quad (Bottom)
        glVertex3f(0.0f,0.0f, 1.0f);			// Top Left Of The Quad (Bottom)
        glVertex3f(0.0f,0.0f,0.0f);			// Bottom Left Of The Quad (Bottom)
        glVertex3f( 1.0f,0.0f,0.0f);			// Bottom Right Of The Quad (Bottom)
        
        glNormal3f( 0.0f, 0.0f, 1.0f );
        glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Front)
        glVertex3f(0.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Front)
        glVertex3f(0.0f,0.0f, 1.0f);			// Bottom Left Of The Quad (Front)
        glVertex3f( 1.0f,0.0f, 1.0f);			// Bottom Right Of The Quad (Front)

        glNormal3f( 0.0, 0.0, -1.0f );
        glVertex3f( 1.0f,0.0f,0.0f);			// Bottom Left Of The Quad (Back)
        glVertex3f(0.0f,0.0f,0.0f);			// Bottom Right Of The Quad (Back)
        glVertex3f(0.0f, 1.0f,0.0f);			// Top Right Of The Quad (Back)
        glVertex3f( 1.0f, 1.0f,0.0f);			// Top Left Of The Quad (Back)

        glNormal3f( 1.0, 0.0, 0.0 );
        glVertex3f(0.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Left)
        glVertex3f(0.0f, 1.0f,0.0f);			// Top Left Of The Quad (Left)
        glVertex3f(0.0f,0.0f,0.0f);			// Bottom Left Of The Quad (Left)
        glVertex3f(0.0f,0.0f, 1.0f);			// Bottom Right Of The Quad (Le

        glNormal3f(-1.0, 0.0, 0.0 );
        glVertex3f( 1.0f, 1.0f,0.0f);			// Top Right Of The Quad (Right)
        glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Right)
        glVertex3f( 1.0f,0.0f, 1.0f);			// Bottom Left Of The Quad (Right)
        glVertex3f( 1.0f,0.0f,0.0f);			// Bottom Right Of The Quad (Right)*/
    glEnd();

    glutSolidCube(1.0);
}

void initScene()
{
    glMatrixMode(GL_PROJECTION);

    // Cull faces
    glEnable( GL_CULL_FACE );
    glFrontFace( GL_CCW );
    glEnable(GL_DEPTH_TEST);

    DEBUG("Renderer") << "Enabled geometry culling, counterclockwise" << ENDLOG;

    // Texturing
 //   glEnable( GL_TEXTURE_2D );
//    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );        // byte pixel row align

    DEBUG("Renderer") << "Enabled 2d textures" << ENDLOG;

    // Perspective transform
    float perspective = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
    gluPerspective( 90.0, perspective, 0.1, 100.0 );

    DEBUG("Renderer") << "Set perspective, "
                      << "fov=" << 90.0 << ", "
                      << "ratio=" << perspective << ", "
                      << "near=" << 0.1 << ", "
                      << "far=" << 100.0 << ENDLOG;

    // Set model view matrix
    glMatrixMode(GL_MODELVIEW);

    // Set up lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    DEBUG("Renderer") << "Enabled light 0 at 0.5, 5.0, 7.0, 1.0" << ENDLOG;

    checkForErrors();
}

void resizeScene(int width, int height)
{
    // Make sure we don't divide by zero (can this actually happen?)
    if( height == 0 )
    {
        raiseError("Window height is set to zero? How did that happen?");
    }

    float ratio = static_cast<float>(width) /
                  static_cast<float>(height);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport( 0, 0, width, height );

    // Set correct perspective
    gluPerspective( DEFAULT_FOV, ratio, 0.1, 100.0 );


    DEBUG("Renderer") << "Window resized. "
                      << "new_size=" << width << "x" << height << ", "
                      << "fov=" << 90.0 << ", "
                      << "ratio=" << ratio << ", "
                      << "near=" << 0.1 << ", "
                      << "far=" << 100.0 << ENDLOG;

    // Reset model view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    checkForErrors();
}

bool checkForErrors()
{
    GLenum error = glGetError();

    if( error != GL_NO_ERROR )
    {
        std::cout << "OpenGL Error: "
                  << (char*) gluErrorString( error )
                  << std::endl;
    }

    assert( error == 0 );
}

void handleKeyboard( unsigned char key, int x, int y )
{
    INFO("gui") << "Keyboard pressed, key "
                << static_cast<int>(key)
                << ENDLOG;

    switch ( key )
    {
        case KEY_ESC:
            std::cout << "Goodbye!" << std::endl;
            glutLeaveMainLoop();
            break;

        case 119: // W
            GCamera.moveForward();
            break;

        case 97: // A
            GCamera.strafeLeft();
            break;

        case 115: // S
            GCamera.moveBackward();
            break;

        case 100: // D
            GCamera.strafeRight();
            break;

        default:
            std::cout << "Unhandled button '"
                      << static_cast<int>(key)
                      << "'"
                      << std::endl;
            break;
    }
}

void handleSpecialKeys( int key, int mx, int my )
{
    float rotate_y = 0.0f, rotate_x = 0.0f;
    bool displayCameraInfo = false;

    switch ( key ) 
    {
        case GLUT_KEY_F2:
            GCamera.printDebugInfo();
            break;

        case GLUT_KEY_F5:
            GCamera.reset();
            break;

        case GLUT_KEY_LEFT:
            rotate_y = 25.0f;
            break;
        case GLUT_KEY_RIGHT:
            rotate_y = -25.0f;
            break;
        case GLUT_KEY_UP:
            rotate_x = 25.0f;
            break;
        case GLUT_KEY_DOWN:
            rotate_x -= 25.0f;
            break;

        default:
            std::cout << "Unhandled special key: " << key << std::endl;
            break;
    }

    GCamera.addMouseLookDelta( rotate_x, rotate_y );
}

void mouseMovement( int x, int y )
{
    static int lastX = -1;
    static int lastY = -1;

    if ( lastX == -1 && lastY == -1 ) { lastX = x; lastY = y; return; }

    int deltaX = x - lastX;
    int deltaY = y - lastY;

    lastX      = x;
    lastY      = y;

    GCamera.addMouseLookDelta( deltaY, -deltaX ); //deltaY/10 );
}

void handleMouseWheel( int button, int dir, int x, int y )
{
    if ( dir > 0 )
    {
        GCamera.moveForward();      // or "zoom" or are they the same?
    }
    else
    {
        GCamera.moveBackward();
    }
}
