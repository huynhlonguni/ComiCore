import { useEffect } from "react";
import Module from "../editor"

const Canvas = () => {
	const loadWASM = async () => {
        let editor = await Module({
			canvas: document.getElementById('canvas')
		});
     }

    useEffect(() => {
        loadWASM();
    }, []);

    return (
        <div className="w-full bg-gray-500">
            <canvas id="canvas" onContextMenu={ (event) => event.preventDefault() } tabIndex="-1"/>            
        </div>
    );
};

export default Canvas;