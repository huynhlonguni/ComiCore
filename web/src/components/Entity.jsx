import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faImage, faComment, faICursor } from "@fortawesome/free-solid-svg-icons";
import clsx from "clsx";

const Entity = ({type, className}) => {
	const icon = faImage;
	if (type == 1) icon = faComment;
	else if (type == 2) icon = faICursor;

	return(
		<div className="w-full h-8 flex gap-2 px-8 py-4 place-items-center">
			<FontAwesomeIcon icon={icon} size="lg" className={`${className} text-white `}/>
			<div className="text-white">Item</div>
		</div>
	)
}

export default Entity;