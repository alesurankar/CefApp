

export interface CefApi {
  // App
  MouseClickFunc(): void;
  // TitleBar
  CloseFunc(): void;
  MinimizeFunc(): void;
  ResizeFunc(): void;
  // BodyFrame
  CreateD3DWindowFunc(): void;
  SetHandleXFunc(x: number): void;
  SpawnTabWindowFunc(): void;
}
const cef = window as unknown as CefApi;

// App
export function myCefMouseClick(): void { cef.MouseClickFunc(); }
// TitleBar
export function myCefClose(): void { return cef.CloseFunc(); }
export function myCefMinimize(): void { return cef.MinimizeFunc(); }
export function myCefResize(): void { return cef.ResizeFunc(); }
// BodyFrame
export function myCefCreateD3DWindow(): void { cef.CreateD3DWindowFunc(); }
export function myCefSetHandleX(x: number): void { cef.SetHandleXFunc(x); }
export function myCefSpawnTabWindow(): void { cef.SpawnTabWindowFunc(); }
