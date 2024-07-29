import './App.css';
import ToolBar from './components/ToolBar';
import EntityBar from './components/EntityBar';
import PropertyBar from './components/PropertyBar';
import Canvas from './components/Canvas';

function App() {
  return (
    <div className="flex flex-col w-screen h-screen">
      <ToolBar/>
      <div className="flex justify-between w-full h-full min-h-0">
        <EntityBar />
        <Canvas className="w-full h-full m-0 p-0 border-0 bg-gray-500"/>
        <PropertyBar />
      </div>
    </div>
  );
}

export default App;
