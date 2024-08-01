import { useEffect, useState, useSyncExternalStore } from "react";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faImage, faComment, faICursor } from "@fortawesome/free-solid-svg-icons";
import clsx from "clsx";

const Entity = ({type, className, id}) => {
	const numPanel = useSyncExternalStore(subscribe, getPanelCount);
	const [panel, setPanel] = useState(window.editor?._EditorGetAttachmentPanel(id));

	useEffect(() => {
		setPanel(window.editor?._EditorGetAttachmentPanel(id));
	}, [window.editor?._EditorGetAttachmentPanel(id)]);

	let icon = faImage;
	if (type == 1) icon = faComment;
	else if (type == 2) icon = faICursor;

	return(
		<div className="w-full h-8 flex justify-between px-4 py-8 border-b border-zinc-700 place-items-center">
			<div className="flex place-items-center gap-2">
				<FontAwesomeIcon icon={icon} size="lg" className={`${className} text-white `}/>
				<div className="text-white">Attachment #{id + 1}</div>
			</div>
			<select
				className="bg-zinc-800 text-white outline-none border border-zinc-700 rounded-lg p-1"
				value={panel}
				onChange={(e) => {
					setPanel(e.target.value)
					window.editor?._EditorSetAttachmentPanel(id, e.target.value)
			}}>
				<option key={-1} value={-1}>Outside</option>
				{
					[...Array(numPanel)].map((e, i) => {
						return <option key={i} value={i}>Panel #{i + 1}</option>
					})
				}
			</select>
		</div>
	)
}

function getPanelCount() {
	return window.editor?._EditorGetPanelCount() ?? 0;
}

function subscribe(callback) {
	window.addEventListener('EditorStateChangeEvent', callback);
	return () => {
		window.removeEventListener('EditorStateChangeEvent', callback);
	};
}

export default Entity;