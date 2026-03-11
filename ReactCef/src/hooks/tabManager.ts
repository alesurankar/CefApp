import { useState } from "react";

export interface Tab {
  id: number;
  title: string;
}

export const tabManager = () => {
  const [tabs, setTabs] = useState<Tab[]>([]);

  const spawnTab = () => {
    const newTab: Tab = { id: Date.now(), title: `Tab ${tabs.length + 1}` };
    setTabs([...tabs, newTab]);
  };

  const closeTab = (id: number) => {
    setTabs(tabs.filter(tab => tab.id !== id));
  };

  return { tabs, spawnTab, closeTab };
};