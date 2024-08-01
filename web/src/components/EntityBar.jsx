import { useSyncExternalStore } from "react";
import Entity from "./Entity";


const EntityBar = () => {
	const numAttachment = useSyncExternalStore(subscribe, getAttachmentCount);
	console.log(numAttachment);
	return(
		<div className="w-96 h-full bg-zinc-800 border border-zinc-700">
			{
				[...Array(numAttachment)].map((e, i) => {
					const type = window.editor?._EditorGetAttachmentType(i);
					return <Entity key={i} id={i} type={type}/>
				})
			}
		</div>
	)
};

function getAttachmentCount() {
	return window.editor?._EditorGetAttachmentCount() ?? 0;
}

function subscribe(callback) {
	window.addEventListener('EditorStateChangeEvent', callback);
	return () => {
		window.removeEventListener('EditorStateChangeEvent', callback);
	};
}

export default EntityBar;
