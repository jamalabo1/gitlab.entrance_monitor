import React, {useEffect, useMemo, useRef} from 'react';
import * as signalR from "@microsoft/signalr";
import {HubConnectionState} from "@microsoft/signalr";
import './styles/App.css';
import './styles/app.scss';

interface IOpenCV {
    [key: string]: any;
}

declare const cv: IOpenCV;


function App() {


    const connection = useMemo(() => {
        return new signalR.HubConnectionBuilder()
            .withUrl("http://localhost:5165/subscribe")
            .build()
    }, []);

    const $canvas = useRef<HTMLCanvasElement>(null);

    useEffect(() => {
        if (connection.state === HubConnectionState.Disconnected) {
            connection.start().then(() => {
                console.log('Connected to signal-R');
                connection.invoke("SubscribeToTopic", {
                    TopicName: "frames.{1}"
                });
                connection.on("ReceiveFrame", (data) => {
                    if (typeof (cv) !== 'undefined' && $canvas.current !== null) {
                        if (cv) {
                            let image = new Image()
                            image.src = `data:image/jpeg;base64,${data}`;
                            image.onload = () => {
                                if ($canvas.current) {
                                    const ctx = $canvas.current.getContext("2d");
                                    ctx?.drawImage(image, 0, 0);
                                }
                                // const mat = cv.imread(image);
                                // cv.imshow($canvas.current, mat);
                                // mat.delete();
                            }
                        }
                    }
                    // receiving frame data
                });
            });
        }
    }, []);


    return (
        <div className="bg-dark vh-100 d-flex justify-content-center align-items-center">
            <div className="container">
                <div className='text-center'>
                    <div className='h2 text-white pb-3'>
                        Entrance Monitor
                    </div>

                    <canvas width={415} height={415} ref={$canvas}/>
                </div>
            </div>
        </div>
    );
}

export default App;
