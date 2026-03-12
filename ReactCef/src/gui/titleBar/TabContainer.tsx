import { myCefSetHandleX, } from "../../cef/cefInterface.ts"
import { useEffect, useRef } from "react";
import Icon from "../../icons/Icon.tsx";


interface Tab {
  id: number;
  title: string;
}
interface TabContainerProps {
  tabs: Tab[];
  closeTab: (id: number) => void;
}

const TabContainer: React.FC<TabContainerProps> = ({ tabs, closeTab }) => {
  const tabRefs = useRef<(HTMLDivElement | null)[]>([]);

  useEffect(() => {
    const handle = requestAnimationFrame(() => {
      let width = 0;
      tabRefs.current.forEach(tab => {
        if (tab) width += tab.offsetWidth + 20;
      });
      myCefSetHandleX(width);
    });

    return () => cancelAnimationFrame(handle);
  }, [tabs]);

  return (
    <div className="flex flex-1 items-center overflow-x-auto space-x-0.5 px-0.5">
      {tabs.map((tab, idx) => (
        <div
          key={tab.id}
          ref={el => { tabRefs.current[idx] = el; }}
          className="flex items-center text-[#a8a8a8] hover:text-[#ffffff] bg-[#373737] hover:bg-[#202020]"
        >
          <span className="text-sm px-2 ">{tab.title}</span>
          <button
            title="close"
            className="hover:bg-[#1177bb] my-1 mx-0.5 rounded"
            onClick={() => closeTab(tab.id)}
          ><Icon name="x_mark" size={15}/>
          </button>
        </div>
      ))}
    </div>
  );
};

export default TabContainer;