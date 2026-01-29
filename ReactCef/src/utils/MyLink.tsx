interface Props {
    title?: string;
    MyClassName?: string;
    onClick?: () => void;
}

const MyLink = (props: Props) => {
  return (
    <a
        onClick={props.onClick}
        className={`text-[#063816] hover:text-[#18602f] font-bold text-[1.4rem] transition duration-300 ${props.MyClassName}`}
        style={{ textShadow: "0 0 20px #62d486" }} 
        onMouseEnter={e => e.currentTarget.style.textShadow = "0 0 10px #79f09f"}
        onMouseLeave={e => e.currentTarget.style.textShadow = "0 0 20px #62d486"}
        >
        {props.title}
    </a>
  );
};

export default MyLink