import { useEffect } from "react";
import Module from "../editor"

const Canvas = ({className}) => {
	const loadWASM = async () => {
        const canvas = document.getElementById("canvas");
        window.editor = await Module({
            canvas: canvas
        });
        canvas.width = canvas.clientWidth;
        canvas.height = canvas.clientHeight;
        window.addEventListener ("resize", function (e) {
            canvas.width = canvas.clientWidth;
            canvas.height = canvas.clientHeight;
        }, true);
    }

    useEffect(() => {
        loadWASM();
    }, []);

    return (
        <canvas className={className} id="canvas"
                onContextMenu={ (event) => event.preventDefault() } tabIndex="-1"
        />         
    );
};

export default Canvas;