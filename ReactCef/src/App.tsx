import { useState, useEffect } from "react";
import TitleBar from './gui/titleBar/TitleBar.tsx';
import FooterBar from './gui/FooterBar.tsx';
import BodyContainer from './gui/bodyContainer/BodyContainer.tsx';
import { myCefMouseClick } from "./cef/cefInterface.ts"


interface Tab {
  id: number;
  title: string;
}

const App = () => {
  const [tabs, setTabs] = useState<Tab[]>([]);

  const spawnTab = () => {
    const newTab: Tab = { id: Date.now(), title: `Tab ${tabs.length + 1}` };
    setTabs([...tabs, newTab]);
  };

  const closeTab = (id: number) => {
    setTabs(tabs.filter(tab => tab.id !== id));
  };

  useEffect(() => {
    document.addEventListener("mousedown", myCefMouseClick);
    return () => document.removeEventListener("mousedown", myCefMouseClick);
  }, []);

  return (
    <div className="flex flex-col h-screen w-screen overflow-hidden">
      <TitleBar tabs={tabs} closeTab={closeTab} />
      <BodyContainer tabs={tabs} spawnTab={spawnTab} />
      <FooterBar />
    </div>
  );
};

export default App;
