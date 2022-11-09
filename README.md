# 2023 KSURCT Autonomous Vehicle Team
</br>

## PDF page for the Competition
https://www.thenrc.org/uploads/7/1/5/1/71512601/nrccontestrules2023.pdf (pages 14-18)

<br></br>

## TO RUN THE ROBOT FROM THE PI
`python3 run.py # in the root of the repository while in virtual environment`
</br>

## To Use the Virtual Environment DOESNT WORK IN WONDOWS AT THE MOMENT
- Windows (WIP):`python -m venv venv`
            `venv\Scripts\activate`
            `pip install -r requirements.txt`

- Linux:    `python3 -m venv venv`
            `source venv/bin/activate`
            `pip install -r requirements.txt`

#### Robot Dir:
- has files for running the robot and calculating algorithms

#### teeny Dir:
- code for the micro controller and sensors

#### Solidworks Dir:
- TODO

#### Test Dir:
- For testing

#### OpenCV:
- if we decide to use camera this will hold all of the files for image processing

### Development
Push all changes to develop branch
Main branch holds stable and tested code