import { myCefSetHandleX, } from "../../cef/cefInterface.ts"
import { useEffect, useRef } from "react";
import Icon from "../icons/Icon.tsx";


interface Tab {
  id: number;
  title: string;
}
interface TabContainerProps {
  tabs: Tab[];
  closeTab: (id: number) => void;
}

const TabContainer: React.FC<TabContainerProps> = ({ tabs, closeTab }) => {
  const containerRef = useRef<HTMLDivElement | null>(null);

  useEffect(() => {
    const handle = requestAnimationFrame(() => {
      if (!containerRef.current) return;
      
      const widthCssPx = containerRef.current.scrollWidth;
      const widthNativePx = Math.round(widthCssPx * window.devicePixelRatio);
      myCefSetHandleX(widthNativePx);
    });

    return () => cancelAnimationFrame(handle);
  }, [tabs.length]);

  return (
    <div className="flex-1 overflow-x-auto">
      <div 
        ref={containerRef}
        className="flex w-max items-center">
        {tabs.map((tab) => (
          <div
            key={tab.id}
            className="border border-gray-800 flex items-center text-[#a8a8a8] hover:text-[#ffffff] bg-[#373737] hover:bg-[#202020]"
          ><span className="text-sm px-2 ">{tab.title}</span>
          
            <button
              title="close"
              className="hover:bg-[#1177bb] my-1 mx-0.5 rounded"
              onClick={() => closeTab(tab.id)}
            ><Icon name="x_mark" size={15}/>
            </button>
          </div>
        ))}
      </div>
    </div>
  );
};

export default TabContainer;