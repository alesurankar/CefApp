import TitleBar from './gui/TitleBar.tsx';
import FooterBar from './gui/FooterBar.tsx';
import BodyFrame from './gui/BodyFrame.tsx';

const App = () => {
  return (
    <div id="window-container" className="flex flex-col h-screen">
      <TitleBar />
      <BodyFrame className="flex-1 overflow-auto" />
      <FooterBar />
    </div>
  );
};

export default App;
