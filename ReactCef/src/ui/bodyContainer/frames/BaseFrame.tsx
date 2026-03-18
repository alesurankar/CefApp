
interface BaseFrameProps {
  title: string;
  visible: boolean;
  children: React.ReactNode;
  className?: string;
}

const BaseFrame = ({ title, visible, children, className }: BaseFrameProps) => {
  if (!visible) return null;

  return (
    <div className={`bg-white text-black items-center justify-center ${className}`}>
      <h2 className="text-xl font-bold mb-4 text-center">{title}</h2>
      {children}
    </div>
  );
};

export default BaseFrame;