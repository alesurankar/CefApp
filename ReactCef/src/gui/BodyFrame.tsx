interface BodyFrameProps {
  className?: string;
}

const BodyFrame: React.FC<BodyFrameProps> = ({ className }) => {
  return (
    <div className={`bg-gray-900 text-white p-4 ${className ?? ''}`}>
      <p>Lots of content here...</p>
      {[...Array(50)].map((_, i) => (
        <p key={i}>Line {i + 1}</p>
      ))}
    </div>
  );
};

export default BodyFrame;
