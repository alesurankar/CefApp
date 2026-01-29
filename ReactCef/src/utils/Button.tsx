interface Props {
    type?: "button" | "submit" | "reset";
    title?: string;
    MyClassName?: string;
    onClick?: () => void;
}

const Button = (props: Props) => {
    return (
        <button
            type={props.type}
            onClick={props.onClick}
            className={`w-40 h-12 lg:w-52 lg:h-16 flex bg-[#7c2923] hover:bg-[#d5453a] items-center justify-center rounded-xl cursor-pointer text-[1.2rem] text-white ${props.MyClassName ?? ""}`}
            >
            {props.title}
        </button>
    )
}

export default Button