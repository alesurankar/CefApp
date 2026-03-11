import TabContainer from "./TabContainer.tsx";
import WindowControls from "./WindowControls.tsx";

interface Tab {
    id: number;
    title: string;
}

interface TitleBarProps {
    tabs: Tab[];
    closeTab: (id: number) => void;
}

const TitleBar: React.FC<TitleBarProps> = ({ tabs, closeTab }) => {

  return (
    <div className="h-8 w-full flex items-center justify-between bg-[#202020] text-white select-none">
      <TabContainer tabs={tabs} closeTab={closeTab}/>

      <WindowControls />
    </div>
  );
};

export default TitleBar;
