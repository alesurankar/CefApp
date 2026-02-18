import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import { HashRouter  } from 'react-router-dom';
import TitleBar from './gui/TitleBar.tsx';
import FooterBar from './gui/FooterBar.tsx';
import BodyFrame from './gui/BodyFrame.tsx';
import './index.css'
//import App from './App.tsx'

createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <HashRouter>
      <div
        id="window-container"
        className="flex flex-col h-screen"
      >
        <TitleBar />
        <BodyFrame className="flex-1 overflow-auto" />
        <FooterBar />
      </div>
    </HashRouter>
  </StrictMode>,
)