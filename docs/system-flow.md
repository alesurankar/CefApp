
```text
EntryPoint
  │
  ├── Application
  │   app.run();   [SYNC] blocks until app exits
  │
  ├── new MyCefApp();      [SYNC] just allocates the CEF app object
  │   CefExecuteProcess(); [SYNC] subprocess check, [ASYNC] internally for subprocesses
  │
  ├── CefInitialize()       [SYNC] initializes CEF, returns after threads start
  │      ├── Browser Thread [ASYNC]
  │      ├── IO Thread      [ASYNC]
  │      └── GPU Thread     [ASYNC]
  │
  ├── Create MainWindow     [SYNC] window and child controls are created
  │      ├── Create WindowTitleBar [SYNC]
  │      └── Create BrowserView    [SYNC] constructs object
  │            ├── new MyCefClient        [SYNC] object creation only
  │            └── CefBrowserHost::CreateBrowser  [ASYNC] browser window created asynchronously
  │
  └── RunMessageLoop();  [SYNC] runs until WM_QUIT received
  ```