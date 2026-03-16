
interface FooterProps {
  className?: string;
}

const FooterBar: React.FC<FooterProps> = ({ className }) => {

  return (
    <div className={`items-center justify-between bg-[#007acc] ${className}`}>
      <p className="pl-10 pb-1 text-sm truncate">Footer</p>
    </div>
  );
};

export default FooterBar