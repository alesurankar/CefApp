import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import { HashRouter  } from 'react-router-dom';
import TitleBar from './gui/TitleBar.tsx';
import './index.css'
//import App from './App.tsx'

createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <HashRouter>
      <div id="window-container" style={{ display: 'flex', flexDirection: 'column', height: '100vh' }}>
        <TitleBar />
        {/* <div style={{ flex: 1, position: 'relative', overflow: 'hidden' }}>
          <App />
        </div> */}
      </div>
    </HashRouter>
  </StrictMode>,
)