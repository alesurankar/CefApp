interface Props {
    type?: "button" | "submit" | "reset";
    title?: string;
    titleClassName?: string;
    color?: string;
    mainClassName?: string;
    onClick?: () => void;
}

const Button = (props: Props) => {
    return (
        <button
            type={props.type}
            onClick={props.onClick}
            className={`${props.mainClassName} w-40 h-12 lg:w-52 lg:h-16 flex items-center justify-center rounded-xl cursor-pointer`}
            >
            <span className={`${props.titleClassName} text-lg text-textColor`}>{props.title}</span>
        </button>
    )
}

export default Button