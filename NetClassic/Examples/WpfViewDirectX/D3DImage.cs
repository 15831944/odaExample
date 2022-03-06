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
using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media;
using Teigha.GraphicsSystem;
using Teigha.Runtime;

namespace WpfViewDirectX
{

  public class WpfViewDirectXD3DImage : D3DImage
  {
    private Device m_gsDevice;
    private IntPtr d3dSurfacePtr = IntPtr.Zero; // pointer to a native IDirect3DSurface which we get from gs device
    private static System.Reflection.MethodInfo fSetBackBuffer = null; // for vc10 compatibility

    public WpfViewDirectXD3DImage()
    {
    }

    public void Initialize(Device device)
    {
      m_gsDevice = device;
    }

    public void UpdateSurface()
    {
      if (m_gsDevice == null)
        return;

      if (IsSoftwareOnlyRenderMode() && !this.IsFrontBufferAvailable)
        return;

      UpdateBackBuffer();
    }

    void UpdateBackBuffer()
    {
      d3dSurfacePtr = GetD3DSurfaceFromDevice();
      SetD3DSurfacePtrToBackBuffer(d3dSurfacePtr);
    }

    /// <summary>
    /// Get D3DSurface object from the Device.
    /// Before calling get, should update the device, so property also will be updated.
    /// At the moment of update, previous D3DSurface should be disposed.
    /// </summary>
    private IntPtr GetD3DSurfaceFromDevice()
    {
      RXObject d3dSurfaceProp = null;
      using (Dictionary props = m_gsDevice.Properties)
      {
        if (props.Contains("D3DSurface"))
          d3dSurfaceProp = props["D3DSurface"];
      }

      if (d3dSurfaceProp == null)
        return IntPtr.Zero;

      RxVariant v = new RxVariant(d3dSurfaceProp);
      return v.IntPtr;
    }

    private void SetD3DSurfacePtrToBackBuffer(IntPtr realSurfacePointer)
    {
      if (realSurfacePointer == IntPtr.Zero)
        return;

      CallSetBackBufferWithLocks(realSurfacePointer);

      UpdateDirtyRect();
    }

    private void CallSetBackBufferWithLocks(IntPtr surface)
    {
      // Next call should look like:
      //
      //SetBackBuffer(
      //  D3DResourceType.IDirect3DSurface9,
      //  WpfViewDirectXSurface.UnmanagedObject,
      //  RenderOptions.ProcessRenderMode == System.Windows.Interop.RenderMode.SoftwareOnly
      //);
      //
      // To keep compatibility with vc10 and .NET Framework 4, where this method is private:
      //

      // get the method if it had not got before
      if (fSetBackBuffer == null)
        fSetBackBuffer = typeof(WpfViewDirectXD3DImage).GetMethod("SetBackBuffer", new Type[] { typeof(D3DResourceType), typeof(IntPtr), typeof(bool) });

      this.Lock();

      // call the method
      fSetBackBuffer.Invoke(this, new object[] {
        D3DResourceType.IDirect3DSurface9,
        surface,
        RenderOptions.ProcessRenderMode == System.Windows.Interop.RenderMode.SoftwareOnly
      });

      this.Unlock();
    }

    private void UpdateDirtyRect()
    {
      Int32Rect updateRect = new Int32Rect();
      updateRect.X = updateRect.Y = 0;
      updateRect.Width = this.PixelWidth;
      updateRect.Height = this.PixelHeight;

      this.Lock();
      this.AddDirtyRect(updateRect);
      this.Unlock();
    }

    public void ClearBackBufferAndSurface()
    {
      CallSetBackBufferWithLocks(IntPtr.Zero);
      
      if (d3dSurfacePtr != IntPtr.Zero)
      {
        Marshal.Release(d3dSurfacePtr);
        d3dSurfacePtr = IntPtr.Zero;
      }
    }

    public void Deinitialize()
    {
      if (IsSoftwareOnlyRenderMode() &&  !this.IsFrontBufferAvailable)
        return;

      if (m_gsDevice == null)
        return;

      ClearBackBufferAndSurface();

      m_gsDevice.Dispose();
      m_gsDevice = null;
    }

    private bool IsSoftwareOnlyRenderMode()
    {
      return RenderOptions.ProcessRenderMode == System.Windows.Interop.RenderMode.SoftwareOnly;
    }
  }

}
