/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#import <AppKit/AppKit.h>

#include "OdaCommon.h"
#include <OpenGL/GL.h>

#define USE_FBO

#ifdef USE_FBO
bool GLES2_ParseExtension(const char *pExtName, const char *pExtensions);
#endif

@interface GLES2OffscreenRenderer : NSObject
{
  NSOpenGLPixelFormat* m_format;
  NSOpenGLPixelBuffer* m_pb;
#ifdef USE_FBO
  GLuint m_rBuf;
  GLuint m_dBuf;
  GLuint m_fbo;
#endif
  NSOpenGLContext* m_ctx;
@public
  unsigned m_width, m_height;
}
@property (retain) NSOpenGLContext* m_ctx;
-(id)initWithParams:(unsigned)width withHeight:(unsigned)height;
-(void)uninit;
-(GLuint)getM_fbo;
@end

@implementation GLES2OffscreenRenderer : NSObject
{
#ifndef __clang__
  NSOpenGLPixelFormat* m_format;
  NSOpenGLPixelBuffer* m_pb;
#ifdef USE_FBO
  GLuint m_rBuf;
  GLuint m_dBuf;
  GLuint m_fbo;
#endif
  NSOpenGLContext* m_ctx;
@public
  unsigned m_width, m_height;
#endif
}
@synthesize m_ctx;
-(id)initWithParams:(unsigned)width withHeight:(unsigned)height
{
  NSOpenGLPixelFormatAttribute attributes[] =
  {
    NSOpenGLPFAPixelBuffer,
    //NSOpenGLPFANoRecovery,
    NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)24,
    NSOpenGLPFAStencilSize, (NSOpenGLPixelFormatAttribute)8,
    (NSOpenGLPixelFormatAttribute)0
  };
  
  m_format = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
  m_ctx = [[NSOpenGLContext alloc] initWithFormat:m_format shareContext:nil];
  ODA_ASSERT(m_ctx != nil);
#ifdef USE_FBO
  [m_ctx makeCurrentContext];
  if (GLES2_ParseExtension("GL_EXT_framebuffer_object", NULL))
  {
    ::glGenRenderbuffersEXT(1, &m_dBuf);
    ::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_dBuf);
    ::glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH24_STENCIL8_EXT, width, height);
    ::glGenRenderbuffersEXT(1, &m_rBuf);
    ::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_rBuf);
    ::glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA8, width, height);
    ::glGenFramebuffersEXT(1, &m_fbo);
    ::glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
    ::glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, m_rBuf);
    ODA_ASSERT(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) == GL_FRAMEBUFFER_COMPLETE_EXT);
    ::glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_dBuf);
    ::glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_dBuf);
  }
  else
  {
    m_fbo = 0;
#else
  {
#endif
    m_pb = [[NSOpenGLPixelBuffer alloc] initWithTextureTarget:GL_TEXTURE_RECTANGLE_EXT textureInternalFormat:GL_RGBA textureMaxMipMapLevel:0 pixelsWide:width pixelsHigh:height];
    ODA_ASSERT(m_pb != nil);
    [m_ctx setPixelBuffer:m_pb cubeMapFace:0 mipMapLevel:0 currentVirtualScreen:[m_ctx currentVirtualScreen]];
  }
  m_width = width; m_height = height;
  return self;
}
-(void)uninit
{
#ifdef USE_FBO
  if (m_fbo != 0)
  {
    ::glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    ::glDeleteFramebuffersEXT(1, &m_fbo);
    ::glDeleteRenderbuffersEXT(1, &m_rBuf);
    ::glDeleteRenderbuffersEXT(1, &m_dBuf);
  }
#endif
  [m_ctx clearDrawable];
  [m_format release];
  [m_ctx release];
#ifdef USE_FBO
  if (m_fbo == 0)
#endif
  {
    [m_pb release];
  }
}
-(GLuint)getM_fbo
{
	return m_fbo;
}
@end

// C++ wrappers
void *odGLES2AttachCocoaPB(unsigned width, unsigned height)
{
  return (void*)[[GLES2OffscreenRenderer alloc] initWithParams:width withHeight:height];
}

void odGLES2DetachCocoaPB(void *pObj)
{
  id objId = (id)pObj;
  GLES2OffscreenRenderer *m_ctx = objId;
  [m_ctx uninit];
  [m_ctx release];
}

void odGLES2MakeCurrentCocoaPB(void *pObj)
{
  id objId = (id)pObj;
  GLES2OffscreenRenderer *m_ctx = objId;
  [m_ctx.m_ctx makeCurrentContext];
}

bool odGLES2CheckDimsCocoaPB(void *pObj, unsigned width, unsigned height)
{
  id objId = (id)pObj;
  GLES2OffscreenRenderer *m_ctx = objId;
  return (m_ctx->m_width == width) && (m_ctx->m_height == height);
}

GLuint odGLES2GetFrameBufferInCocoaPB(void *pObj)
{
#ifdef USE_FBO
  id objId = (id)pObj;
  GLES2OffscreenRenderer *m_ctx = objId;
  return [m_ctx getM_fbo];
#else
  return 0;
#endif
}

//
