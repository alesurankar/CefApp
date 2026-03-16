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
}

const BodyContainer: React.FC<BodyContainerProps> = ({ views, activeViewId, spawnView }) => {

  return (
    <div className="flex flex-1 overflow-auto">
      <NavigationBar spawnView={spawnView}/>
      <MainFrameArea views={views} activeViewId={activeViewId}/>
    </div>
  );
};

export default BodyContainer;
