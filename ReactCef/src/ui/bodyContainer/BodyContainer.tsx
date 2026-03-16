import NavigationBar from "./NavigationBar.tsx";
import MainFrameArea from "./MainFrameArea.tsx";


interface View {
  id: number;
  title: string;
  type?: string;
}
interface BodyContainerProps {
  views: View[];
  activeViewId: number | null;
  spawnView: () => void;
  className?: string;
}

const BodyContainer: React.FC<BodyContainerProps> = ({ views, activeViewId, spawnView, className }) => {

  return (
    <div className={`${className}`}>
      <NavigationBar 
        spawnView={spawnView} 
        className="flex w-12 h-full"
      />
      <MainFrameArea 
        views={views} 
        activeViewId={activeViewId} 
        className="flex flex-1"
      />
    </div>
  );
};

export default BodyContainer;
