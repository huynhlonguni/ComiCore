import { useState, useSyncExternalStore } from "react";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faImage, faComment, faICursor } from "@fortawesome/free-solid-svg-icons";
import clsx from "clsx";

const Entity = ({type, className, id}) => {
	const numPanel = useSyncExternalStore(subscribe, getPanelCount);

	let icon = faImage;
	if (type == 1) icon = faComment;
	else if (type == 2) icon = faICursor;

	return(
		<div className="w-full h-8 flex gap-2 px-4 py-8 border-b border-zinc-700 place-items-center">
			<FontAwesomeIcon icon={icon} size="lg" className={`${className} text-white `}/>
			<div className="text-white">Attachment #{id + 1}</div>
			<select
				className="bg-zinc-800 text-white outline-none border border-zinc-700 rounded-lg p-1"
				value={window.editor?._EditorGetAttachmentPanel(id)}
				onChange={(e) => {
					window.editor?._EditorSetAttachmentPanel(id, e.target.value)
			}}>
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