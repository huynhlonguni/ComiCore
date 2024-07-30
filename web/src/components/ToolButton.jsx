import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import clsx from "clsx";


const ToolButton = ({icon, className, onClick, isActive}) => {
	return(
		<div className={clsx("w-12 h-12", "flex place-items-center justify-center",
			"border-zinc-700 border-r",
			!isActive && "bg-zinc-800 hover:bg-green-900",
			isActive && "bg-green-700"
		)} onClick={onClick}>
			<FontAwesomeIcon icon={icon} size="lg" className={`${className} text-white `}/>
		</div>
	)
};

export default ToolButton;