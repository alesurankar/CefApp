import { useEffect } from "react";
import { tabManager } from './hooks/tabManager';
import { dropdownManager } from "./hooks/dropdownManager.ts";
import { myCefMouseClick } from "./cef/cefInterface"
import TitleBar from './gui/titleBar/TitleBar.tsx';
import BodyContainer from './gui/bodyContainer/BodyContainer.tsx';
import FooterBar from './gui/FooterBar.tsx';
import OverlayLayer from "./gui/overlays/OverlayLayer.tsx";


const App = () => {
  const { tabs, spawnTab, closeTab } = tabManager();
  const { dropdown, toggleDropdown } = dropdownManager();

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
