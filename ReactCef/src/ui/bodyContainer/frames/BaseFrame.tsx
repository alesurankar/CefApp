
interface BaseFrameProps {
  title: string;
  visible: boolean;
}

const BaseFrame: React.FC<BaseFrameProps> = ({ title, visible }) => {

  return (
    <div className={`flex-1 bg-white text-black ${
        visible ? "block" : "hidden"}`}>
      <h2>{title}</h2>
      <div>This is BaseFrame content</div>
    </div>
  );
};

export default BaseFrame;