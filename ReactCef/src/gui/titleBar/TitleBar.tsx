import ViewButton from "./ViewButton.tsx";
import TabContainer from "./TabContainer.tsx";
import WindowControls from "./WindowControls.tsx";


interface Tab {
  id: number;
  title: string;
}
interface TitleBarProps {
  tabs: Tab[];
  closeTab: (id: number) => void;
  toggleDropdown: (x: number, y: number) => void;
}

const TitleBar: React.FC<TitleBarProps> = ({ tabs, closeTab, toggleDropdown }) => {

  return (
    <div className="h-8 w-full flex items-center justify-between bg-[#202020] text-white select-none">
      <div className="flex items-center flex-1 overflow-hidden">
        <ViewButton onClick={toggleDropdown}/>
        <TabContainer tabs={tabs} closeTab={closeTab}/>
      </div>
      <WindowControls />
    </div>
  );
};

export default TitleBar;
