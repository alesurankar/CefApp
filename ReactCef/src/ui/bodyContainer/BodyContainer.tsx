import NavigationBar from "./NavigationBar.tsx";
import MainFrameArea from "./MainFrameArea.tsx";


interface View {
  id: number;
  title: string;
}
interface BodyContainerProps {
  views: View[];
  spawnView: () => void;
}

const BodyContainer: React.FC<BodyContainerProps> = ({ views, spawnView }) => {

  return (
    <div className="flex flex-1 overflow-auto">
      <NavigationBar spawnView={spawnView}/>
      <MainFrameArea views={views}/>
    </div>
  );
};

export default BodyContainer;
