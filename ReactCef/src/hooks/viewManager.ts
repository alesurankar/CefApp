import { useState } from "react";

export interface View {
  id: number;
  title: string;
  type?: "empty" | "D3DWindow";
}

export const viewManager = () => {
  const [views, setViews] = useState<View[]>([]);
  const [activeViewId, setActiveViewId] = useState<number | null>(null); 

  const spawnView  = () => {
    const newView: View = { 
      id: Date.now(), 
      title: `View ${views.length + 1}` 
    };
    setViews([...views, newView]);
    setActiveViewId(newView.id);
  };

  const closeView = (id: number) => {
    setViews(views.filter(view => view.id !== id));
    if (activeViewId === id) setActiveViewId(null);
  };

  const focusView = (id: number) => setActiveViewId(id);

  return { views, activeViewId, spawnView, closeView, focusView };
};