import { myCefSetHandleX, } from "../../cef/cefInterface.ts"
import { useEffect, useRef } from "react";
import Icon from "../icons/Icon.tsx";


interface View {
  id: number;
  title: string;
  type?: string;
}
interface TabContainerProps {
  views: View[];
  activeViewId: number | null;
  closeView: (id: number) => void;
  focusView: (id: number) => void;
}

const TabContainer = ({ views, activeViewId, closeView, focusView }: TabContainerProps) => {
  const containerRef = useRef<HTMLDivElement | null>(null);

  useEffect(() => {
    const handle = requestAnimationFrame(() => {
      if (!containerRef.current) return;
      
      const widthCssPx = containerRef.current.scrollWidth;
      const widthNativePx = Math.round(widthCssPx * window.devicePixelRatio);
      myCefSetHandleX(widthNativePx);
    });

    return () => cancelAnimationFrame(handle);
  }, [views.length]);

  return (
    <div className="flex-1 overflow-x-auto">
      <div 
        ref={containerRef}
        className="flex w-max items-center">
        {views.map((view) => (
          <div
            key={view.id}
            className={`group border border-gray-800 flex items-center ${
              view.id === activeViewId 
              ? "bg-[#202020] text-white" 
              : "bg-[#373737] text-[#a8a8a8] hover:text-white"
            }`}
            onClick={() => focusView(view.id)}
          ><span className="text-sm pl-3 pr-1">{view.title}</span>
          
            <button
              title="close"
              className={`hover:bg-[#1177bb] my-1 mx-0.5 rounded
                ${
                  view.id === activeViewId
                    ? "opacity-100"
                    : "opacity-0 group-hover:opacity-100"
                }`}
              onClick={(e) => { e.stopPropagation(); closeView(view.id); }}
            ><Icon name="x_mark" size={15} />
            </button>
          </div>
        ))}
      </div>
    </div>
  );
};

export default TabContainer;