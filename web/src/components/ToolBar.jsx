import { useState } from "react";
import ToolButton from "./ToolButton";
import { faHouse, faHand, faScissors, faPenNib, faArrowPointer, faComment, faICursor} from "@fortawesome/free-solid-svg-icons";

const ToolBar = () => {
	const [active, setActive] = useState(-2);

	const setTool = (id) => {
		if (window.editor)
			window.editor._EditorSetActiveTool(id);
	}

	return(
		<div className="w-full h-12 bg-zinc-800 border border-zinc-700 flex">
			<ToolButton icon={faHouse} className="" onClick={() => {
				// alert("Go Home");
			}}/>
			<ToolButton icon={faHand} isActive={active == -1} onClick={() => {
				setActive(-1);
				setTool(-1);
			}}/>
			<ToolButton icon={faScissors} isActive={active == 0} onClick={() => {
				setActive(0);
				setTool(0);
			}}/>
			<ToolButton icon={faPenNib} isActive={active == 1} onClick={() => {
				setActive(1);
				setTool(1);
			}}/>
			<ToolButton icon={faArrowPointer} isActive={active == 2} onClick={() => {
				setActive(2);
				setTool(2);
			}}/>
			<ToolButton icon={faComment} isActive={active == 3} onClick={() => {
				setActive(3);
				setTool(3);
			}}/>
			<ToolButton icon={faICursor} isActive={active == 4} onClick={() => {
				setActive(4);
				setTool(4);
			}}/>
		</div>
	)
};

export default ToolBar;
