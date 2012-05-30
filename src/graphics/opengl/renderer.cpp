#include "graphics/opengl/renderer.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <limits>

#include "core/logging.h"
#include "engine/world.h"
#include "engine/cubedata.h"
#include "engine/camera.h"
#include "lodepng.h"

#include "mathlib.h"

#include <cassert>
#include <iostream>

const int DEFAULT_POS = 0;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int DEFAULT_FOV = 90;
const int KEY_ESC = 27;

Camera GCamera;
bool GWireframeRender = false;

void checkForErrors();

//
// renderer setup funcs
//
void initScene();
void resizeScene( int w, int h );

//
// renderer gui funcs
//
void glutIdleFunc();
void handleMenuItemSelection( int id );
void handleKeyboard( unsigned char key, int x, int y );
void handleSpecialKeys( int key, int x, int y );
void handleMouseWheel( int button, int dir, int x, int y );
void drawCube();

//
// render engine functions
//
void doRenderScene();
void calcFPS();

void addLight( int id,
        const Vec3& pos,
        const Vec3& ambient,
        const Vec3& diffuse,
        const Vec3& spec
);
void drawCubeChunk( const CubeChunkMesh& mesh );
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

    GLenum err = glewInit();

    if ( GLEW_OK != err )
    {
        raiseError("Failed to load GLEW");
    }
    else
    {
        DEBUG("Renderer") << "Loading GLEW library" << ENDLOG;
    }

    if (! GLEW_VERSION_2_1 )
    {
        if (! GLEW_VERSION_1_5 )
        {
            raiseError("OpenGL version 1.5 or greater required");
        }
        else
        {
            std::cerr << "WARNING - OLD VERSION OF OPENGL" << std::endl;
        }
    }


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

void calcFPS()
{
    static int lastTime    = 0;
    static int nextTime    = 0;
    static int   frames    = 0;

    static int bestFrameTime  = -1;
    static int worstFrameTime = 0;

    const  int updateInterval = 5000;

    // init
    int nowTime   = glutGet( GLUT_ELAPSED_TIME );
    int deltaTime = nowTime - lastTime;

    if ( lastTime == 0 )
    {
        lastTime  = nowTime;
        nextTime += nowTime + updateInterval;
        return;
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
        float avg = fps / 1000.0f;

        std::cout << fps       << " frames/sec. " 
                  << avg       << "ms average ("
                  << "best: "  << bestFrameTime  << "ms, "
                  << "worst: " << worstFrameTime << "ms)" 
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
void renderScene( /*const*/ World& world )
{
    renderScene( world, GCamera );
}

Vec3 world2gl( const Vec3& v )
{
    return Vec3( v[0], v[2], -v[1] );
}

Vec3 gl2world( const Vec3& v )
{
    return Vec3( v[0], -v[2], v[1] );
}

void renderScene( /*const*/ World& world, const Camera& camera )
{
    // Clear the rendering buffrs
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Reset model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Render in wireframe or solid mode?
    if ( GWireframeRender )
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
    else
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    //
    // Render from the view of the camer
    //
    Vec3 lookAt = camera.direction() * camera.viewDistance();
    Vec3 center = camera.center();
    Vec3 up     = camera.up();

    gluLookAt( center[0], center[1], center[2],
               lookAt[0], lookAt[1], lookAt[2],
               up[0],     up[1],     up[2] );

    //
    // Lets have a light
    //
    addLight( 0,
              Vec3( 0.0, 5.0, 2.0 ),
              Vec3( 0.75, 0.75, 0.75 ),
              Vec3( 1.0, 1.0, 1.0 ),
              Vec3( 1.0, 0.25, 0.25 )
    );

    float diffuse[3] = { 0.75, 0.75, 0.75 };
    float ambient[3] = { 0.25, 0.25, 0.25 };

    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE );
    glMaterialfv( GL_FRONT, GL_AMBIENT, (const GLfloat*) &ambient );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, (const GLfloat*) &diffuse );

    //
    // Yay braindead renderer.
    //
    CubeChunkMesh * mesh = world.getCompiledMesh();
    assert( mesh   != NULL );

    drawCubeChunk( *mesh );

    //
    // Draw a cube to represent the intended construction area
    //
    CubeIntersection intersection = world.firstCubeIntersecting( 
                                           gl2world(camera.center()),
                                           gl2world(camera.direction())
    );

    if ( intersection.distance != std::numeric_limits<float>::infinity() )
    {
        float color[3] = { 0.2f, 0.2f, 0.9f };
        Point newCubePos = intersection.cubepos + intersection.normal;

        glMaterialfv( GL_FRONT, GL_DIFFUSE, (const GLfloat*) &color );

        glPushMatrix();

        glTranslatef( static_cast<float>(newCubePos[0]),
			          static_cast<float>(newCubePos[2]),
					  static_cast<float>(-newCubePos[1]) );
        drawCube();

        glPopMatrix();
    }

    // 
    // Draw a line representing the camera's view
    //
    Vec3 camDirection = camera.direction() * 50;
    Vec3 camCenter    = camera.center();

    glDisable( GL_LIGHTING );

    glPushMatrix();
    glTranslatef( camCenter[0], camCenter[1], camCenter[2] );

    glBegin( GL_LINES );
        glColor3f( 1.0, 0.0, 0.0 );
        glVertex3f( 0.01f, 0.01f, -0.1f );
        glVertex3f( camDirection[0], camDirection[1], camDirection[2] );
    glEnd();

    glPopMatrix();

    //
    // All done, finish up the frame. Make sure there were no errors,
    // calculate some FPS stats and then swap the back buffer
    //
    checkForErrors();
    calcFPS();
    glutSwapBuffers();
}

void addLight(       int   id,
               const Vec3& pos,
               const Vec3& ambient,
               const Vec3& diffuse,
               const Vec3& specular )
{
    //
    // Detect which light to use
    //
    assert( id >= 0 && id < GL_MAX_LIGHTS );
    GLenum light = GL_LIGHT0;

    switch ( id )
    {
        case 0: light = GL_LIGHT0; break;
        case 1: light = GL_LIGHT1; break;
        case 2: light = GL_LIGHT2; break;
        case 3: light = GL_LIGHT3; break;
        case 4: light = GL_LIGHT4; break;
        case 5: light = GL_LIGHT5; break;
        case 6: light = GL_LIGHT6; break;
        case 7: light = GL_LIGHT7; break;
        default:
            assert( false && "bad light" );
    }

    //
    // Enable lighting, and then fill several temporary arrays with
    // the values opengl requies
    //
    glEnable( GL_LIGHTING );
    glEnable( light );

    float vpos[4] = { pos[0],      pos[1],      pos[2],      1.0f };
    float vamb[4] = { ambient[0],  ambient[1],  ambient[2],  1.0f };
    float vdif[4] = { diffuse[0],  diffuse[1],  diffuse[2],  1.0f };
    float vspc[4] = { specular[0], specular[1], specular[2], 1.0f };

    //
    // Let there be light!
    //
    glLightfv( light, GL_POSITION, vpos );
    glLightfv( light, GL_AMBIENT,  vamb );
    glLightfv( light, GL_DIFFUSE,  vdif );
    glLightfv( light, GL_SPECULAR, vspc );
}

/**
 * Given a chube chunk mesh, this function will instruct OpenGL to render
 * it to the screen
 */
void drawCubeChunk( const CubeChunkMesh& mesh )
{
    assert( mesh.vbid      > 0 );
    assert( mesh.ibid      > 0 );
    assert( mesh.faceCount > 0 );

    //
    // Bind our graphics contex to the vertex and index buffers.
    // We're going to be using textures and normals, so make sure to
    // enable all applicable arrays
    //
    glBindBuffer( GL_ARRAY_BUFFER, mesh.vbid );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.ibid );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );

    //
    // Specify pos/texture/normal offset information. This tells OpenGL
    // where specific data is located in the GL_ARRAY_BUFFER data stream
    //
    glVertexPointer(   3, GL_FLOAT, 32, (uint8_t*) 0 );
    glNormalPointer(      GL_FLOAT, 32, (uint8_t*) 12 );
    glTexCoordPointer( 2, GL_FLOAT, 32, (uint8_t*) 24 );

    //
    // Now that we've set everything up properly, actually rendering the
    // mesh is pretty unclimatic. That's it!
    //
    glDrawElements( GL_TRIANGLES, mesh.faceCount, GL_UNSIGNED_INT, 0 );

    //
    // Disable everything we enabled, in the name of being and good citizen
    // and all that. Don't want to pollute the renderer state machine,
    // y'know...
    //
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void drawCube()
{
    //
    // Cube vertex positions. Each set of four vertices is arranged in
    // the following order:
    //
    //   A---D
    //   | / |
    //   B---C
    //
    // Also, the six sets are arrange in [+x,-x,+y,-y,+z,-z] order. This
    // means the vertex soup is arranged like so:
    //   1. right face
    //      1. A0 A1 A2
    //      2. B0 B1 B2
    //      3. C 
    //      4. D ...
    //   2. left face
    //   3. back face
    //   4. front face
    //   5. top face
    //   6. bottom face
    //
    // All vertices are specified in OpenGL coordinates, but are ordered
    // along the game's axis (0..6)
    //
    float CubePos[6][4][3] = 
    {   /* right face */
        { { 1.0f, 1.0f, 0.0f },
          { 1.0f, 0.0f, 0.0f },
          { 1.0f, 0.0f,-1.0f },
          { 1.0f, 1.0f,-1.0f } },
        /* left face */
        { { 0.0f, 1.0f,-1.0f },
          { 0.0f, 0.0f,-1.0f },
          { 0.0f, 0.0f, 0.0f },
          { 0.0f, 1.0f, 0.0f } },
        /* back face */
        { { 1.0f, 1.0f,-1.0f },
          { 1.0f, 0.0f,-1.0f },
          { 0.0f, 0.0f,-1.0f },
          { 0.0f, 1.0f,-1.0f } },
        /* front face */
        { { 0.0f, 1.0f, 0.0f },
          { 0.0f, 0.0f, 0.0f },
          { 1.0f, 0.0f, 0.0f },
          { 1.0f, 1.0f, 0.0f } },
        /* top face */
        { { 1.0f, 1.0f, 0.0f },
          { 1.0f, 1.0f,-1.0f },
          { 0.0f, 1.0f,-1.0f },
          { 0.0f, 1.0f, 0.0f } },
        /* bottom face */
        { { 0.0f, 0.0f, 0.0f },
          { 0.0f, 0.0f,-1.0f },
          { 1.0f, 0.0f,-1.0f },
          { 1.0f, 0.0f, 0.0f } }
    };

    /**
     * Array holding the normal vectors for our cube. Vector details
     * are specified in OpenGL space, but are ordered for game axis.
     */
    float CubeNorms[6][3] =
    {
        { 1.0f,  0.0f,  0.0f },
        {-1.0f,  0.0f,  0.0f },
        { 0.0f,  0.0f, -1.0f },
        { 0.0f,  0.0f,  1.0f },
        { 0.0f,  1.0f,  0.0f },
        { 0.0f, -1.0f,  0.0f }
    };


    glBegin( GL_TRIANGLES );
    for ( int k = 0; k < 6; ++k )
    {
        glNormal3fv( CubeNorms[k] );
        
        glVertex3fv( CubePos[k][1] );
        glVertex3fv( CubePos[k][3] );
        glVertex3fv( CubePos[k][0] );

        glVertex3fv( CubePos[k][2] );
        glVertex3fv( CubePos[k][3] );
        glVertex3fv( CubePos[k][1] );
    }
    glEnd();
}

void initScene()
{
    glMatrixMode(GL_PROJECTION);

    // Cull faces
    glEnable( GL_CULL_FACE );
    glFrontFace( GL_CCW );
    glEnable( GL_DEPTH_TEST );

    DEBUG("Renderer") << "Enabled geometry culling, counterclockwise" << ENDLOG;

    // Texturing
    glEnable( GL_TEXTURE_2D );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );        // byte pixel row align

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

    checkForErrors();
}

void resizeScene(int width, int height)
{
    //
    // Make sure we don't divide by zero (can this actually happen?)
    // /
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

void checkForErrors()
{
    GLenum error   = glGetError();
	bool bHasError = ( error != GL_NO_ERROR );

    if( bHasError )
    {
        std::string msg = std::string("OpenGL Error: ")                       +
			              reinterpret_cast<const char*>(gluErrorString(error));

		raiseError( msg );
    }
}

void handleKeyboard( unsigned char key, int, int )
{
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

void takeScreenshot()
{
    int width        = WINDOW_WIDTH;
    int height       = WINDOW_HEIGHT;
    int bytes        = width * height * 3;
    uint8_t * pixels = new uint8_t[ bytes ];

    glReadBuffer( GL_FRONT );
    glReadPixels( 
            0, 0, 
            width, height, 
            GL_RGB, GL_UNSIGNED_BYTE, 
            pixels
    );

    //
    // PNG library expects image to be top down (not bottom up, as OpenGL
    // likes it). Since I'm feeling lazy and this is only going to be
    // called when we want to take screenshots... well... 
    //
    for ( int h = 0; h < height / 2; ++h )
    {
        int offsetTop    = h * width * 3;
        int offsetBottom = bytes - (h+1) * width * 3;

        for ( int w = 0; w < width; ++w )
        {
            std::swap( pixels[ offsetTop++ ], pixels[ offsetBottom++ ] );
            std::swap( pixels[ offsetTop++ ], pixels[ offsetBottom++ ] );
            std::swap( pixels[ offsetTop++ ], pixels[ offsetBottom++ ] );
        }
    }

    //
    // Save the screenshot in PNG
    //
    LodePNG::Encoder encoder;
    std::vector<uint8_t> buffer;

    encoder.addText("Title",       "A Cubeworld Screenshot");
    encoder.addText("Description", "Screenshot from Cubeworld game");
    encoder.addText("Software",    "Cubeworld");
    encoder.addText("Source",      "Screenshot");
    encoder.addText("Comment",     "Screenshot taken from Cubeworld");

    encoder.getSettings().zlibsettings.windowSize = 2048;
    encoder.infoRaw.color.colorType               = 2;

    // Save it
    encoder.encode( buffer, pixels, width, height );
    LodePNG::saveFile( buffer, "screenshot.png" );

    std::cout << "saved screenshot in screenshot.png" << std::endl;
    delete pixels;
}

void handleSpecialKeys( int key, int, int )
{
    float rotate_y = 0.0f, rotate_x = 0.0f;

    switch ( key ) 
    {
        case GLUT_KEY_F2:
            GCamera.printDebugInfo();
            break;

        case GLUT_KEY_F3:
            break;

        case GLUT_KEY_F4:
            DEBUG("Camera") << "Resetting camera" << std::endl;
            GCamera.reset();
            break;

        case GLUT_KEY_F5:
            if ( GWireframeRender )
            {
                std::cout << "Switching to solid render mode" << std::endl;
                GWireframeRender = false;
            }
            else
            {
                std::cout << "Switching to wireframe render" << std::endl;
                GWireframeRender = true;
            }
            break;

        case GLUT_KEY_F6:
            break;

        case GLUT_KEY_F12:
            takeScreenshot();
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
    static float lastX = -1.0;
    static float lastY = -1.0;
	static bool initOnce = false;

    if ( initOnce )
	{
		lastX    = static_cast<float>(x);
		lastY    = static_cast<float>(y);
		initOnce = true;
		return;
	}

    float deltaX = x - lastX;
    float deltaY = y - lastY;

    lastX      = static_cast<float>(x);
    lastY      = static_cast<float>(y);

    GCamera.addMouseLookDelta( deltaY, -deltaX ); //deltaY/10 );
}

void handleMouseWheel( int, int dir, int, int )
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
