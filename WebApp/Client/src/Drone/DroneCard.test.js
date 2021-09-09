import React from "react";
import { mount, shallow } from "enzyme";
import DroneCard  from "./DroneCard";
import Grid from "@material-ui/core/Grid";
import { render, screen, fireEvent } from "@testing-library/react";


describe("DroneCard ", () => {
  let wrapper;
  let mockFunc;

  beforeEach(() => {
    mockFunc = jest.fn();
    const props = {
      buttonText: "Example Button Text",
      emitEvent: mockFunc,
    };

    wrapper = mount(<DroneCard {...props} />);
  });

  it("should render two Grid", () => {
    const component = shallow(<DroneCard />);
    expect(component.find(Grid).length).toBe(6);
  });

  it("Control LED has been Called ON", () => {
    const props = {
        setDel: mockFunc,
    };

    const { getByRole } = render(<DroneCard {...props} />);
    const myComponent = getByRole("button", { name: /Allumer la led/i });
    expect(myComponent).toBeDefined();
    fireEvent.click(myComponent);
    expect(props.setDel).toHaveBeenCalledTimes(1);
    expect(props.setDel).toHaveBeenCalledWith(3, true);
  });

  it("Control LED has been Called OFF", () => {
    const props = {
        setDel: mockFunc,
    };

    const { getByRole } = render(<DroneCard {...props} />);
    const myComponent = getByRole("button", { name: /Eteindre la led/i });
    expect(myComponent).toBeDefined();
    fireEvent.click(myComponent);
    expect(props.setDel).toHaveBeenCalledTimes(1);
    expect(props.setDel).toHaveBeenCalledWith(3, false);
  });


});
