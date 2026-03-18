import NavigationBar from "./NavigationBar.tsx";
import MainFrameArea from "./MainFrameArea.tsx";


interface View {
  id: number;
  title: string;
  type: "empty" | "D3DWindow";
}
interface BodyContainerProps {
  views: View[];
  activeViewId: number | null;
  spawnView: () => void;
  className?: string;
}

const BodyContainer = ({ views, activeViewId, spawnView, className }: BodyContainerProps) => {

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
