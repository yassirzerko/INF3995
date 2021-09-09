import React from "react";
import renderer from "react-test-renderer";
import { mount, shallow } from "enzyme";
import { Controls } from "./Controls";

import SwarmCommand from "../SwarmCommands/SwarmCommands";
import SwarmStatus from "../SwarmStatus/SwarmStatus";
import ConnexionStatus from "../ConnexionStatus/ConnexionStatus";



describe("Controls ", () => {
  it("should render initial layout", () => {
    const component = shallow(<Controls />);
    expect(component.length).toBe(1);
  });

  it("should render SwarmCommand", () => {
    const component = shallow(<Controls />);
    expect(component.find(SwarmCommand).length).toBe(1);
  });

  it("should render ConnexionStatus", () => {
    const component = shallow(<Controls />);
    expect(component.find(ConnexionStatus).length).toBe(1);
  });

  it("should render SwarmStatus", () => {
    const component = shallow(<Controls />);
    expect(component.find(SwarmStatus).length).toBe(1);
  });


});
