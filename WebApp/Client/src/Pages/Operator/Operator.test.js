import React from "react";
import { shallow } from "enzyme";
import Operator from "./Operator";
import { Navbar } from "../../Components/Navbar/Navbar.js";
import { ControlHeader } from "../../Components/ControlHeader/ControlHeader.js";
import { Footer } from "../../Components/Footer/Footer.js";

describe("Operator Status", () => {
  it("should render initial layout", () => {
    const component = shallow(<Operator />);
    expect(component.getElements()).toMatchSnapshot();
  });

  it("should render Navbar", () => {
    const component = shallow(<Operator />);
    expect(component.find(Navbar).length).toBe(1);
  });

  it("should render ControlHeader", () => {
    const component = shallow(<Operator />);
    expect(component.find(ControlHeader).length).toBe(1);
  });

  it("should render MainPanel", () => {
    const component = shallow(<Operator />);
    expect(component.find(ControlHeader).length).toBe(1);
  });

  it("should render Footer", () => {
    const component = shallow(<Operator />);
    expect(component.find(Footer).length).toBe(1);
  });

  it("Initial States Check", () => {
    const component = shallow(<Operator />);
    expect(component.instance().state.isConnected).toBeFalsy();
    expect(component.instance().state.runningAppId).toBeNull();
    expect(component.instance().state.isRunningAppReady).toBeFalsy();
    expect(component.instance().state.connectedClientsId).toStrictEqual({});
    expect(component.instance().state.runningAppData).toStrictEqual({});
  });
});
