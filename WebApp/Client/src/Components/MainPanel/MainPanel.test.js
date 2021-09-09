import React from "react";
import renderer from "react-test-renderer";
import { mount, shallow } from "enzyme";
import MainPanel from "./MainPanel";

import Accordion from "@material-ui/core/Accordion";
import Grid from "@material-ui/core/Grid";
import Paper from "@material-ui/core/Paper";
import DroneListSection from "../DroneListSection/DroneListSection";

describe("MainPanel", () => {
  it("should render initial layout", () => {
    const component = shallow(<MainPanel />);
    expect(component.getElements()).toMatchSnapshot();
  });

  it("should render six Grids", () => {
    const component = shallow(<MainPanel />);
    expect(component.find(Grid).length).toBe(6);
  });

  it("should render three Papers", () => {
    const component = shallow(<MainPanel />);
    expect(component.find(Paper).length).toBe(5);
  });

  it("should render two Accordion", () => {
    const component = shallow(<MainPanel />);
    expect(component.find(Accordion).length).toBe(4);
  });

  it("should render DroneListSection", () => {
    const component = shallow(<MainPanel />);
    expect(component.find(DroneListSection).length).toBe(1);
  });
});
