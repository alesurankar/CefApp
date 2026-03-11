import { useState, useEffect } from "react";
import TitleBar from './gui/TitleBar.tsx';
import FooterBar from './gui/FooterBar.tsx';
import BodyFrame from './gui/BodyFrame.tsx';
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

  useEffect(() => {
    document.addEventListener("mousedown", myCefMouseClick);
    return () => document.removeEventListener("mousedown", myCefMouseClick);
  }, []);

  return (
    <div className="flex flex-col h-screen w-screen overflow-hidden">
      <TitleBar tabs={tabs} closeTab={(id) => setTabs(tabs.filter(t => t.id !== id))} />
      <BodyFrame className="flex-1 overflow-auto" spawnTab={spawnTab} />
      <FooterBar />
    </div>
  );
};

export default App;
