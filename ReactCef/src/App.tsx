import { useEffect } from "react";
import { viewManager } from './hooks/viewManager';
import { dropdownManager } from "./hooks/dropdownManager.ts";
import { myCefMouseClick } from "./cef/cefInterface"
import TitleBar from './ui/titleBar/TitleBar.tsx';
import BodyContainer from './ui/bodyContainer/BodyContainer.tsx';
import FooterBar from './ui/FooterBar.tsx';
import OverlayLayer from "./ui/overlayLayer/OverlayLayer.tsx";


const App = () => {
  const { views, activeViewId, spawnView, closeView, focusView } = viewManager();
  const { dropdown, toggleDropdown, showDropdown, hideDropdown } = dropdownManager();

  useEffect(() => {
    const handleContextMenu = (e: MouseEvent) => {
      e.preventDefault(); // stops Chrome/CEF default menu
      showDropdown(e.clientX, e.clientY, "other");
    };

    document.addEventListener("mousedown", myCefMouseClick);
    document.addEventListener("contextmenu", handleContextMenu);

    return () => {
      document.removeEventListener("mousedown", myCefMouseClick);
      document.removeEventListener("contextmenu", handleContextMenu);
    };
  }, [showDropdown]);

  return (
    <div className="flex flex-col h-screen w-screen overflow-hidden select-none">
      <TitleBar 
        views={views} 
        activeViewId={activeViewId} 
        closeView={closeView} 
        focusView={focusView} 
        toggleDropdown={toggleDropdown} 
        className="flex h-8 w-full"/>
      <BodyContainer 
        views={views} 
        activeViewId={activeViewId} 
        spawnView={spawnView} 
        className="flex flex-1"/>
      <FooterBar 
        className="flex h-6 w-full"/>
      <OverlayLayer 
        dropdown={dropdown} 
        hideDropdown={hideDropdown} />
    </div>
  );
};

export default App;
