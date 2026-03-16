
interface BaseFrameProps {
  title: string;
}

const BaseFrame: React.FC<BaseFrameProps> = ({ title }) => {

  return (
    <div className="flex-1 bg-white text-black">
      <h2>{title}</h2>
      <div>This is BaseFrame content</div>
    </div>
  );
};

export default BaseFrame;