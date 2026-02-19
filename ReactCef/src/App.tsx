import { useEffect } from "react";
import TitleBar from './gui/TitleBar.tsx';
import FooterBar from './gui/FooterBar.tsx';
import BodyFrame from './gui/BodyFrame.tsx';


interface CefApi {
  MouseClickFunc(): void;
}

const cef = window as unknown as CefApi;

function myCefMouseClick(): void {
  cef.MouseClickFunc();
}

const App = () => {
  useEffect(() => {
    document.addEventListener("mousedown", myCefMouseClick);
    return () => document.removeEventListener("mousedown", myCefMouseClick);
  }, []);
  return (
    <div id="window-container" className="flex flex-col h-screen">
      <TitleBar />
      <BodyFrame className="flex-1 overflow-auto" />
      <FooterBar />
    </div>
  );
};

export default App;
