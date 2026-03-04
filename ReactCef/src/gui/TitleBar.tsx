import { myCefMinimize, myCefResize, myCefClose, myCefSetHandleX, } from "../cef/cefInterface.ts"
import { useEffect, useRef } from "react";

interface Tab {
    id: number;
    title: string;
}
interface TitleBarProps {
    tabs: Tab[];
    closeTab: (id: number) => void;
}

const TitleBar: React.FC<TitleBarProps> = ({ tabs, closeTab }) => {
  const tabRefs = useRef<(HTMLDivElement | null)[]>([]);

  useEffect(() => {
    const handle = requestAnimationFrame(() => {
      let width = 2;
      tabRefs.current.forEach(tab => {
        if (tab) width += tab.offsetWidth + 21;
      });
      myCefSetHandleX(width);
    });

    return () => cancelAnimationFrame(handle);
  }, [tabs]);

  return (
    <div id="titlebar"
      className="h-8 w-full flex items-center justify-between bg-[#202020] text-white select-none"
    >
      {/* Tabs container */}
      <div className="flex-1 flex items-center overflow-x-auto space-x-1 px-1">
          {tabs.map((tab, idx) => (
            <div
              key={tab.id}
              ref={el => { tabRefs.current[idx] = el; }}
              className="flex items-center bg-[#373737] px-2 rounded"
            >
              <span className="text-sm">{tab.title}</span>
              <button
                className="ml-1 text-red-500 hover:text-red-700"
                onClick={() => closeTab(tab.id)}
              >
                ✕
              </button>
            </div>
          ))}
      </div>

      {/* Window controls */}
      <div className="flex">
        <div className="w-12 h-8 flex items-center justify-center"></div>
        <button
          className="w-12 h-8 flex items-center justify-center hover:bg-[#373737]"
          onClick={myCefMinimize}
        >
          ―
        </button>
        <button
          className="w-12 h-8 flex items-center justify-center hover:bg-[#373737]"
          onClick={myCefResize}
        >
          ☐
        </button>
        <button
          className="w-12 h-8 flex items-center justify-center hover:bg-red-600"
          onClick={myCefClose}
        >
          ✕
        </button>
      </div>
    </div>
  );
};

export default TitleBar;
