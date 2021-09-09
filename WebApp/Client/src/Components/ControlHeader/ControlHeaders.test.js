import React from "react";
import { mount, shallow } from "enzyme";
import { ControlHeader } from "./ControlHeader";
import { Controls } from "../Controls/Controls";

describe("ControlHeaders ", () => {
  it("should render initial layout", () => {
    const component = mount(<ControlHeader />);
    expect(component.length).toBe(1);
  });

  it("should render Controls", () => {
    const component = shallow(<ControlHeader />);
    expect(component.find(Controls).length).toBe(1);
  });

  it("should have scroll listener", () => {
    const handleScroll = jest.fn();
    const component = mount(<ControlHeader />);
    const customEvent = new Event("scroll");
    component.first().getDOMNode().dispatchEvent(customEvent);
    expect(handleScroll).toBeDefined();
  });
});
