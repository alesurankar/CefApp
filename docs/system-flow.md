
EntryPoint
  │
  ├── Application
  │   app.run();   [SYNC]
  │
  ├── new MyCefApp();
  │   CefExecuteProcess();
  │
  ├── CefInitialize()
  │      ├── Browser Thread     [ASYNC]
  │      ├── IO Thread          [ASYNC]
  │      └── GPU Thread         [ASYNC]
  │
  ├── std::make_unique<MainWindow>();   [SYNC]
  └── RunMessageLoop();                 [SYNC]