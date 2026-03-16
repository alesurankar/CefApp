import { useEffect } from "react";
import { tabManager } from './hooks/tabManager';
import { dropdownManager } from "./hooks/dropdownManager.ts";
import { myCefMouseClick } from "./cef/cefInterface"
import TitleBar from './ui/titleBar/TitleBar.tsx';
import BodyContainer from './ui/bodyContainer/BodyContainer.tsx';
import FooterBar from './ui/FooterBar.tsx';
import OverlayLayer from "./ui/overlayLayer/OverlayLayer.tsx";


const App = () => {
  const { tabs, spawnTab, closeTab } = tabManager();
  const { dropdown, toggleDropdown, showDropdown, hideDropdown } = dropdownManager();

  useEffect(() => {
    const handleContextMenu = (e: MouseEvent) => {
      e.preventDefault(); // stops Chrome/CEF default menu
      showDropdown(e.clientX, e.clientY);
    };

    document.addEventListener("mousedown", myCefMouseClick);
    document.addEventListener("contextmenu", handleContextMenu);

    return () => {
      document.removeEventListener("mousedown", myCefMouseClick);
      document.removeEventListener("contextmenu", handleContextMenu);
    };
  }, [showDropdown]);

  return (
    <div className="flex flex-col h-screen w-screen overflow-hidden">
      <TitleBar tabs={tabs} closeTab={closeTab} toggleDropdown={toggleDropdown} />
      <BodyContainer tabs={tabs} spawnTab={spawnTab} />
      <FooterBar />
      <OverlayLayer dropdown={dropdown} hideDropdown={hideDropdown} />
    </div>
  );
};

export default App;
