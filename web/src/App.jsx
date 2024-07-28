import './App.css';
import ToolBar from './components/ToolBar';
import EntityBar from './components/EntityBar';
import PropertyBar from './components/PropertyBar';
import Canvas from './components/Canvas';

function App() {
  return (
    <div className="flex flex-col w-full h-screen">
      <ToolBar/>
      <div className="flex w-full h-full">
        <EntityBar />
        <Canvas />
        <PropertyBar />
      </div>
    </div>
  );
}

export default App;
