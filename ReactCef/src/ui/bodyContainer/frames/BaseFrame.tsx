
interface BaseFrameProps {
  title: string;
  visible: boolean;
  className?: string;
}

const BaseFrame: React.FC<BaseFrameProps> = ({ title, visible, className }) => {
  if (!visible) return null;

  return (
    <div className={`bg-white text-black items-center justify-center ${className}`}>
      <div className="text-center">
        <h2>{title}</h2>
        <div>This is BaseFrame content</div>
      </div>
    </div>
  );
};

export default BaseFrame;