import ViewButton from "./ViewButton.tsx";
import TabContainer from "./TabContainer.tsx";
import WindowControls from "./WindowControls.tsx";


interface View {
  id: number;
  title: string;
  type?: string;
}
interface TitleBarProps {
  views: View[];
  activeViewId: number | null;
  closeView: (id: number) => void;
  focusView: (id: number) => void;
  toggleDropdown: (x: number, y: number) => void;
  className?: string;
}

const TitleBar = ({ views, activeViewId, closeView, focusView, toggleDropdown, className }: TitleBarProps) => {

  return (
    <div className={`items-center justify-between bg-[#202020] text-white select-none ${className}`}>
      <div className="flex items-center flex-1 overflow-hidden">
        <ViewButton onClick={toggleDropdown}
        />
        <TabContainer 
          views={views} 
          activeViewId={activeViewId} 
          closeView={closeView} 
          focusView={focusView} 
        />
      </div>
      <WindowControls />
    </div>
  );
};

export default TitleBar;
