import React from "react";
import { mount, shallow } from "enzyme";
import SwarmCommands from "./SwarmCommands";
import Button from "@material-ui/core/Button";
import { render, screen, fireEvent } from "@testing-library/react";
import TextField from '@material-ui/core/TextField';

describe("Send Commands", () => {
  let commandsId = {
    takeOff: 0,
    land: 1,
    startMission: 2,
    returnToBase: 3,
    softwareUpdate: 4,
  };

  let wrapper;
  let mockFunc;

  beforeEach(() => {
    mockFunc = jest.fn();
    const props = {
      emitEvent: mockFunc,
    };

    wrapper = mount(<SwarmCommands {...props} />);
  });

  it("Should have 7 buttons rendered", () => {
    const button = wrapper.find(Button);
    expect(button).toHaveLength(7);
  });

  it("Initial States Check", () => {
    const component = shallow(<SwarmCommands />);
    expect(component.instance().state.isStartAppPressed).toBeFalsy();
    expect(component.instance().state.isSoftwareUpdatePressed).toBeFalsy();

  });



  it("Start Mission Has been Called", () => {
    const sendCommand = jest.fn();

    const { getByText } = render(
      <Button
                        fullWidth={true}
                        variant="contained"
                        color="default"
                        size="medium"
                        disabled="false"
                        onClick={sendCommand(commandsId.startMission)}>
                        Start Mission
      </Button>


    );

    const node = getByText("Start Mission");
    fireEvent.click(node);

    expect(sendCommand).toHaveBeenCalledTimes(1);
    expect(sendCommand).toHaveBeenCalledWith(commandsId.startMission);

  });


  it("Take Off Has been Called", () => {
    const sendCommand = jest.fn();

    const { getByText } = render(
      <Button
                        fullWidth={true}
                        variant="contained"
                        color="default"
                        size="medium"
                        disabled="false"
                        onClick={sendCommand(commandsId.takeOff)}>
                        Take-off
      </Button>


    );

    const node = getByText("Take-off");
    fireEvent.click(node);

    expect(sendCommand).toHaveBeenCalledTimes(1);
    expect(sendCommand).toHaveBeenCalledWith(commandsId.takeOff);

  });



  it("Return to base Has been Called", () => {
    const sendCommand = jest.fn();

    const { getByText } = render(
      <Button
                        fullWidth={true}
                        variant="contained"
                        color="default"
                        size="medium"
                        disabled="false"
                        onClick={sendCommand(commandsId.returnToBase)}>
                        Return to base
      </Button>


    );

    const node = getByText("Return to base");
    fireEvent.click(node);

    expect(sendCommand).toHaveBeenCalledTimes(1);
    expect(sendCommand).toHaveBeenCalledWith(commandsId.returnToBase);

  });



  it("Emergency Land has been Called", () => {
    const sendCommand = jest.fn();

    const { getByText } = render(
      <Button
                        fullWidth={true}
                        variant="contained"
                        color="default"
                        size="medium"
                        disabled="false"
                        onClick={sendCommand(commandsId.land)}>
                        Land
      </Button>


    );

    const node = getByText("Land");
    fireEvent.click(node);

    expect(sendCommand).toHaveBeenCalledTimes(1);
    expect(sendCommand).toHaveBeenCalledWith(commandsId.land);

  });




  it("onStopApp been Called", () => {
    const onStopApp = jest.fn();

    const { getByText } = render(
      <Button onClick={onStopApp}>Reset App</Button>
    );

    const node = getByText("Reset App");
    fireEvent.click(node);

    expect(onStopApp).toHaveBeenCalledTimes(1);
  });


  it("onStartApp been Called", () => {
    const onStartApp = jest.fn();

    const { getByText } = render(
      <Button onClick={onStartApp}>Start App</Button>
    );

    const node = getByText("Start App");
    fireEvent.click(node);

    expect(onStartApp).toHaveBeenCalledTimes(1);
  });


  it("Software Update has been Called", () => {
    const onSoftwareUpdate = jest.fn();

    const { getByText } = render(
      <Button onClick={onSoftwareUpdate}>Software Update</Button>
    );

    const node = getByText("Software Update");
    fireEvent.click(node);

    expect(onSoftwareUpdate).toHaveBeenCalledTimes(1);
  });

  it('Drone Selector Test', () => {

    const props = {
      isRunningAppReady: true
    };


      const wrapper = shallow(<SwarmCommands  {...props} />);

      expect(wrapper.find(TextField).props().defaultValue).toEqual(2);
      expect(wrapper.find(TextField).props().label).toEqual('Select Number of Drones');
      expect(wrapper.find(TextField).props().disabled).toBeTruthy();


  });


});
