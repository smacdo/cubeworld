cmake_minimum_required(VERSION 2.6)
project(lzma)

add_definitions( -D_LZMA_SIZE_OPT -D_LZMA_PROB32 -D_7ZIP_ST)

add_library( lzma STATIC
             LzmaDec.h
             LzmaDec.c
             LzmaEnc.h
             LzmaEnc.c
             Types.h
             LzFind.c
             LzFind.h
             LzFind.c
             LzFind.h
             LzHash.h )
