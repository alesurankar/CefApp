import { useEffect, useState } from "react";
import { tabManager } from './hooks/tabManager';
import { myCefMouseClick } from "./cef/cefInterface"
import TitleBar from './gui/titleBar/TitleBar.tsx';
import BodyContainer from './gui/bodyContainer/BodyContainer.tsx';
import FooterBar from './gui/FooterBar.tsx';
import OverlayLayer from "./gui/overlays/OverlayLayer.tsx";


const App = () => {
  const { tabs, spawnTab, closeTab } = tabManager();

  const [dropdown, setDropdown] = useState<{ visible: boolean; x: number; y: number }>({
    visible: false,
    x: 0,
    y: 0,
  });

  const toggleDropdown = (e: React.MouseEvent) => {
    setDropdown(prev => ({
      visible: !prev.visible, // ✅ use previous state
      x: e.clientX,
      y: e.clientY,
    }));
  };

  useEffect(() => {
    document.addEventListener("mousedown", myCefMouseClick);
    return () => document.removeEventListener("mousedown", myCefMouseClick);
  }, []);

  return (
    <div className="flex flex-col h-screen w-screen overflow-hidden">
      <TitleBar tabs={tabs} closeTab={closeTab} toggleDropdown={toggleDropdown} />
      <BodyContainer tabs={tabs} spawnTab={spawnTab} />
      <FooterBar />
      <OverlayLayer dropdown={dropdown} />
    </div>
  );
};

export default App;
