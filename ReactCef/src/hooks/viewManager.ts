import { useState } from "react";
import type { View, ViewKind } from "../types/view";


export const viewManager = () => {
  const [views, setViews] = useState<View[]>([]);
  const [activeViewId, setActiveViewId] = useState<number | null>(null); 

  const spawnView  = (kind: ViewKind) => {
    const newView: View = { 
      id: Date.now(), 
      title: `View ${views.length + 1}`,
      kind,
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